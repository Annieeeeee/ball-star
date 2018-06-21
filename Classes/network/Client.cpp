#include <stdio.h>
#include "Client.h"
#include "MessageCode.h"

int ipindex;                                ///能正确连接的ip地址在ip列表里的索引
int serverIndex;                            ///server所在的ip地址在ip列表里的索引
int client_mode;                            ///当前client的运行模式

std::string                 ipOut;          ///能成功建立连接的ip地址字符串
std::string                 currentIp;      ///当前连接的ip地址字符串
std::vector<std::string>    ipList;         ///所有连接到该网段的设备的ip地址表
std::vector<std::string>    serverIpList;   ///能够连接上的, 存在server的ip地址表

static Client*              this_client = nullptr;      ///指向client对象的指针
void chat_client::handle_connect(const boost::system::error_code& error)
{

	if (!error)
	{
		serverIndex = ipindex;
		serverIpList.push_back(ipOut);
		boost::asio::async_read(socket_,
			boost::asio::buffer(read_msg_.data(), chat_message::header_length),
			boost::bind(&chat_client::handle_read_header, this,
				boost::asio::placeholders::error));
	}
	else {

	}
}

void chat_client::handle_write(const boost::system::error_code& error)
{
	if (!error)
	{
		write_msgs_.pop_front();
		if (!write_msgs_.empty())
		{
			boost::asio::async_write(socket_,
				boost::asio::buffer(write_msgs_.front().data(),
					write_msgs_.front().length()),
				boost::bind(&chat_client::handle_write, this,
					boost::asio::placeholders::error));
		}
	}
	else
	{
		do_close();
	}
}


void chat_client::handle_read_header(const boost::system::error_code& error)
{
	if (!error && read_msg_.decode_header())
	{
		boost::asio::async_read(socket_,
			boost::asio::buffer(read_msg_.body(), read_msg_.body_length()),
			boost::bind(&chat_client::handle_read_body, this,
				boost::asio::placeholders::error));
	}
	else
	{
		do_close();
	}
}

void chat_client::handle_read_body(const boost::system::error_code& error)
{
	if (!error)
	{
		std::string temp1(read_msg_.body());
		if (temp1 == ipOut) {                                 /*我明白了！*/
			serverIndex = ipindex;                          /*确定哪个是开了客户端的！*/
															//            std::cout << ipOut << " succeed \n";
															//            std::cout << "==========================\n";
		}
		this_client->t_lock.lock();
		std::string temp(read_msg_.body(), read_msg_.body_length());
		//        std::cout << "client get: " << temp << "==========";

		this_client->_orderList.push_back(temp);
		this_client->t_lock.unlock();
		std::cout.write(read_msg_.body(), read_msg_.body_length());
		//        std::cout << "\n";

		boost::asio::async_read(socket_,
			boost::asio::buffer(read_msg_.data(), chat_message::header_length),
			boost::bind(&chat_client::handle_read_header, this,
				boost::asio::placeholders::error));
	}
	else
	{
		do_close();
	}
}

void chat_client::do_write(chat_message msg)
{
	bool write_in_progress = !write_msgs_.empty();
	write_msgs_.push_back(msg);
	if (!write_in_progress)//一开始是空的，然后pushback进去一条，保证一次只发一个
	{
		boost::asio::async_write(socket_,
			boost::asio::buffer(write_msgs_.front().data(),
				write_msgs_.front().length()),
			boost::bind(&chat_client::handle_write, this,
				boost::asio::placeholders::error));
	}
}

int Client::client(void)
{
	if (system(NULL)) {
		puts("Ok");
	}
	else {
		exit(EXIT_FAILURE);
	}

	if (client_mode == 2)//局域网
	{
		system("ping -c 1 255.255.255.255");
		//        std::cout << "ping done" << std::endl;
		system("arp -a > arp.txt");
		//        std::cout << "arp done" << std::endl;

		std::ifstream in("arp.txt");
		if (in.is_open())
		{
			bool start_read = false;
			while (!in.eof())
			{
				start_read = false;
				std::string temp;
				//                      std::cout << "temp open" << std::endl;
				getline(in, temp);
				if (in.eof()) {
					break;
				}
				if (temp.size() >= 3)
				{
					if (temp[4] == ':')//读取接口ipv4 直接ping这个就可以
					{
						start_read = true;
						//             std::cout << temp;
					}
				}
				if (start_read == true)
				{
					int i = temp.find(' ', 6);
					temp = temp.substr(6, i - 6);
					//                 std::cout << temp << std::endl;
					currentIp = temp;
					ipList.push_back(temp);
				}

			}
		}

	}


	for (int i = 0; i < ipList.size() - 1; i++)
	{

		if (client_mode == 1)
		{
			break;
		}

		if (ipList.size() == 0) {
			return 0;
		}

		bool if_wrong = false;
		int point_count = 0;

		for (int j = 0; j < ipList.at(i).size(); j++)
		{
			if (ipList.at(i).at(j) > '9' || ipList.at(i).at(j) < '0')
			{
				if (ipList.at(i).at(j) != '.')
				{
					if_wrong = true;
					break;
				}

				if (ipList.at(i).at(j) == '.')
				{
					point_count++;
				}

			}
		}

		if (point_count != 3 || if_wrong)
		{
			continue;
		}


		boost::asio::io_service io_service;

		tcp::resolver resolver(io_service);
		tcp::resolver::query query(ipList.at(i), "11332");//serverip和端口
		ipOut = ipList.at(i);
		tcp::resolver::iterator iterator = resolver.resolve(query);//iterator==endpoint_iterator

		chat_client c(io_service, iterator);

		boost::thread t(boost::bind(&boost::asio::io_service::run, &io_service));//run跑io_service

		ipindex = i;

		//usleep(100000);

		c.close();//run完了就关闭
		t.join();//线程结束，可以删了
	}

	if (ipList.size() != 0) {
		//        std::cout << ">>>>>>>>" << ipList.at(serverIndex) << ">>>>>>>>>>\n";
	}


	try
	{

		boost::asio::io_service io_service;

		tcp::resolver resolver(io_service);

		std::string ip;

		if (client_mode == 1)//互联网下
		{
			ip = "115.159.90.65";//上海市上海市 腾讯云 
		}
		else {
			ip = ipList.at(serverIndex);//局域网下
		}
		_search_finished = true;//配好远程服务端
		tcp::resolver::query query(ip, "11332");
		tcp::resolver::iterator iterator = resolver.resolve(query);

		chat_client c(io_service, iterator);
		_clientInstance = &c;
		this_client = this;

		boost::thread t(boost::bind(&boost::asio::io_service::run, &io_service));

		char line[chat_message::max_body_length + 1];
		while (1)
		{
			;
		}//这有什么济儿用处

		c.close();
		t.join();
	}
	catch (std::exception& e)//异常抛出
	{
		std::cerr << "Exception: " << e.what() << "\n";
	}

	return 0;

}

void Client::runClient(int mode)
{
	client_mode = mode;
	_search_finished = false;
	_filter_mode = false;
	std::thread t(&Client::client, this);
	t.detach();
}

void Client::sendMessage(const std::string & code, const std::string & message)
{
	chat_message msg;
	std::string temp;

	if (_filter_mode == true && code[0] != ANSWER_FOR_ROOM[0])
	{
		temp.append(sensitive_word.substr(0, 4));
	}
	temp.append(code);
	temp.append(message);
	msg.body_length(temp.size());
	memcpy(msg.body(), temp.c_str(), msg.body_length());
	msg.encode_header();
	_clientInstance->write(msg);
}

std::string Client::executeOrder(void)
{
	t_lock.lock();
	std::string temp;

	if (_orderList.size() != 0) {
		//        std::cout << "order list :" << _orderList.front() << std::endl;
		temp = _orderList.front();
		_orderList.pop_front();
		if (_filter_mode == true) {
			std::string filter_word = temp.substr(0, 4);
			if (filter_word == sensitive_word.substr(0, 4)) {
				std::string real_order = temp.substr(4, temp.size() - 4);
				temp = real_order;
			}
			else if (temp[0] != QUERY_FOR_ROOM[0])
			{
				temp = "no";
			}
		}
	}
	else {
		temp = "no";
	}
	t_lock.unlock();


	return temp;
}