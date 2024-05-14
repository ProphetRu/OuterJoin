#ifdef _WIN32
#ifndef _WIN32_WINNT
#define _WIN32_WINNT 0x0601
#endif // _WIN32_WINNT
#endif // _WIN32

#include <boost/asio/co_spawn.hpp>
#include <boost/asio/detached.hpp>
#include <boost/asio/io_context.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/signal_set.hpp>
#include <boost/asio/write.hpp>

#include <iostream>

#include "DBMS.h"
#include "SQLHandler.h"
#include "SQLInsert.h"
#include "SQLTruncate.h"

using boost::asio::ip::tcp;
using boost::asio::awaitable;
using boost::asio::co_spawn;
using boost::asio::detached;
using boost::asio::use_awaitable;
namespace this_coro = boost::asio::this_coro;

DBMS g_DBMS;
SQLHandler g_SQLHandler;
unsigned short g_Port{};

constexpr auto BUFF_SIZE{ 1024 };

awaitable<void> HandleClient(tcp::socket client_socket) noexcept
{
	try
	{
		for (;;)
		{
			std::string request(BUFF_SIZE, '\0');
			co_await async_write(client_socket, boost::asio::buffer("> "), use_awaitable);

			if (const auto request_size = co_await client_socket.async_read_some(boost::asio::buffer(request), use_awaitable); request_size > 1)
			{
				request.resize(request_size - 1);

				try
				{
					if (auto query{ g_SQLHandler.Handle(request) }; query->GetType() == SQLType::Insert)
					{
						const auto query_ptr{ dynamic_cast<SQLInsert*>(query.get()) };
						g_DBMS.Insert(query_ptr->GetTableName(), query_ptr->GetRecord());
					}
					else if (query->GetType() == SQLType::Truncate)
					{
						const auto query_ptr{ dynamic_cast<SQLTruncate*>(query.get()) };
						g_DBMS.Truncate(query_ptr->GetTableName());
					}
					else if (query->GetType() == SQLType::Intersection)
					{
						for (const auto table{ g_DBMS.Intersection() }; const auto & [index, filelds] : table)
						{
							// because github actions don't support std::format :(
							std::string msg = std::to_string(index) + "," + filelds.first + "," + filelds.second + "\n";
							co_await async_write(client_socket, boost::asio::buffer(msg), use_awaitable);
						}
					}
					else if (query->GetType() == SQLType::SymmetricDifference)
					{
						for (const auto table{ g_DBMS.SymmetricDifference() }; const auto & [index, filelds] : table)
						{
							// because github actions don't support std::format :(
							std::string msg = std::to_string(index) + "," + filelds.first + "," + filelds.second + "\n";
							co_await async_write(client_socket, boost::asio::buffer(msg), use_awaitable);
						}
					}

					co_await async_write(client_socket, boost::asio::buffer("< OK\n"), use_awaitable);
				}
				catch (const std::exception& ex)
				{
					// because github actions don't support std::format :(
					std::string msg = "< ERR ";
					msg += ex.what();
					msg += "\n";
					write(client_socket, boost::asio::buffer(msg));
				}
			}
		}
	}
	catch (const std::exception& ex)
	{
		std::cerr << "Exception: " << ex.what() << std::endl;
	}
}

awaitable<void> Listener() noexcept
{
	auto executor = co_await this_coro::executor;
	tcp::acceptor acceptor(executor, { tcp::v4(), g_Port });

	for (;;)
	{
		auto client_socket = co_await acceptor.async_accept(use_awaitable);

		co_spawn(executor, HandleClient(std::move(client_socket)), detached);
	}
}

int main(int argc, char* argv[]) noexcept
{
	if (argc != 2)
	{
		std::cout << "Usage: " << argv[0] << " <port>\n";
		return -1;
	}

	try
	{
		g_Port = static_cast<unsigned short>(std::stoi(argv[1]));
		if (g_Port > 65534)
		{
			throw std::runtime_error("Invalid port");
		}

		g_DBMS.AddTable("A");
		g_DBMS.AddTable("B");

		boost::asio::io_context io_context(1);

		boost::asio::signal_set signals(io_context, SIGINT, SIGTERM);

		signals.async_wait([&](auto, auto) { io_context.stop(); });

		co_spawn(io_context, Listener(), detached);

		io_context.run();
	}
	catch (const std::exception& ex)
	{
		std::cerr << "Exception: " << ex.what() << std::endl;
	}
	
	return 0;
}
