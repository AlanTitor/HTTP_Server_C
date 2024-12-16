#include"tests.h"


int test_WSAStartup_error(WSADATA wsadata){
    if(WSAStartup(MAKEWORD(2,2), &wsadata) != 0){
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), RED);//Меняем цвет на красный
        perror("WSAStartup failed\n");
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);//Меняем цвет на белый
        return 1;} //Инициализируем использование сокетов в Windows
    return 0;
}

int test_socket_error(SOCKET server_socket){
    if(server_socket == -1){
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), RED);//Меняем цвет на красный
        perror("Couldn't create socket\n");
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);//Меняем цвет на белый
        closesocket(server_socket);
        WSACleanup();
        return 1;}//Выдаем сам сокет (если вернет -1, то ошибка)
    return 0;
}

int test_bind_error(SOCKET server_socket, struct sockaddr_in server_addr){
    if(bind(server_socket,(struct sockaddr *)&server_addr, sizeof(server_addr)) != 0){//Привязываем текущий сокет к нашим данным
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), RED);//Меняем цвет на красный
        perror("Bind faild");
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);//Меняем цвет на белый
        closesocket(server_socket);
        WSACleanup();
        return 1;
    }
    return 0;
}

int test_listen_error(SOCKET server_socket){
    if(listen(server_socket, 3) < 0){//начинаем слушать порт
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), RED);//Меняем цвет на красный
        perror("Listen failed");
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);//Меняем цвет на белый
        closesocket(server_socket);
        WSACleanup();
        return 1;
    }
    return 0;
}

char test_file_error(FILE *file){
    if(file == NULL){
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), RED);//Меняем цвет на крассный
        perror("Can't open file!\n");
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);//Меняем цвет на белый
        fclose(file);
        return 1;
    }
    return 0;
}

char test_content_error(char *content, FILE *file){
    if(content == NULL){
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), RED);//Меняем цвет на крассный
        perror("Can't get memory!\n");
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);//Меняем цвет на белый
        fclose(file);
        free(content);
        return 1;
    }
    return 0;
}

char test_bytes_read_error(size_t bytes_read, LONG file_size, FILE *file, char *content){
    if(bytes_read >= file_size){
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), RED);//Меняем цвет на крассный
        perror("Can't read file!\n");
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);//Меняем цвет на белый
        fclose(file);
        free(content);
        return 1;
    }
    return 0;
}

void test_recive_error(int recive){
    if(recive < 0){
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), RED);//Меняем цвет на крассный
        perror("Received failed\n");
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);//Меняем цвет на белый
        return;
    }
}

void test_html_content_error(char *html_content){
    if(html_content == NULL){
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), RED);//Меняем цвет на крассный
            perror("Can't read content");
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);//Меняем цвет на белый
            return;
        }
}

void test_http_response_error(char *http_response, SOCKET client_socket, char *html_content){
    if(http_response == NULL){
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), RED);//Меняем цвет на крассный
            perror("Can't get memory for http!");
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);//Меняем цвет на белый
            closesocket(client_socket);
            free(html_content);
            return;
        }
}