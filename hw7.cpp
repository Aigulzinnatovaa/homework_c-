#include <iostream >
#include <boost/asio.hpp >
#include <ctime>
#include <cstdlib>



using namespace boost::asio;
using ip::tcp;

class Session : public std::enable_shared_from_this<Session > {
    public: Session(tcp::socket socket) : socket_(std::move(socket))

{
}

void start() {
    do_read();
}

private:
void do_read() {
    auto self(shared_from_this());
    socket_ .async_read_some(buffer(data_, max_length), [this, self](boost::system::error_code ec, std::size_t length) {
                if (!ec) {
                    handle_request(length);
                }
            });
}

void do_write(std::string message) {
    auto self(shared_from_this());
    async_write(socket_, buffer(message), [this, self](boost::system::error_code ec, std::size_t /*length*/) {
                if (!ec) {
                    do_read();
                }
            });
}

void handle_request(std::size_t length) {
    std:: string request(data_, length - 2);
    // remove \r\n std::string response;
    if (request == "username")

{
    response = "Username: " + get_username();
}

else if (request == "hostname") {
    response = "Hostname: " + get_hostname();
}

else {
    response = "Invalid command";
}

response + = "\r\n";
do_write(response);
}

std::string get_username() {
    return "user";
}

std::string get_hostname() {
    char hostname[1024];
    gethostname(hostname, 1024);
    return hostname;
}

tcp::socket socket_;
enum {
    max_length = 1024
}

;
char data_[max_length];
}

;

class Server {
    public: Server(io_service& io_service, short port) : acceptor_(io_service, tcp::endpoint(tcp::v4(), port))

{
    do_accept();
}

private:
void do_accept() {
    acceptor_ .async_accept( [this](boost::system::error_code ec, tcp::socket socket) {
                if (!ec) {
                    std::make_shared<Session>(std::move(socket))->start();
                }

                do_accept();
            });
}

tcp::acceptor acceptor_;
}

;

int main() {
    try
    time_t now = time(0);
    char* dt = ctime(&now);
    cout << "The local date and time is: " << dt << endl;
    tm *gmtm = gmtime(&now);
    dt = asctime(gmtm);
    cout << "The UTC date and time is:"<< dt << endl;
    string command = "ls ~/";
    system(command.c_str());
    return 0;

{
    io_service io_service;
    Server server(io_service, 12345);
    io_service .run();
}

catch (std::exception& e) {
    std:: cerr << "Exception: " << e.what() << "\n";
}

return 0;
}
