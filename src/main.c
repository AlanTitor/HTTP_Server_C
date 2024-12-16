#include"server.h"

#define BUFFER_SIZE 1024

enum colors color; 


int main(){

    printf("Enter the port number: ");
    UINT PORT;
    scanf("%u", &PORT);
    

    WSADATA wsadata = {0};
    test_WSAStartup_error(wsadata);

    SOCKET server_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);//IPv4/tcp протокол для сокета
    test_socket_error(server_socket);

    struct sockaddr_in server_info;//настраиваем информацию о свервере
    server_info.sin_family = AF_INET;//Указывает IPv4
    server_info.sin_addr.s_addr = INADDR_ANY;//Храним наш IP аддрес
    server_info.sin_port = htons(PORT);//Устанавливаем порт который будем слушать

    test_bind_error(server_socket, server_info);//Привязываем сокет к адресу
    test_listen_error(server_socket);
    

    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), YELLOW);//Меняем цвет на желтый
    printf("Server is listening on port %d\n", PORT);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);//Меняем цвет на белый


    while(TRUE){
        struct sockaddr_in client_addr;//храним адресс и порт клиента
        int client_addr_len = sizeof(client_addr);
        SOCKET client_socket = accept(server_socket, (struct sockaddr *)&client_addr, &client_addr_len);//Ожидает подключение к server_socket 
        if(client_socket == INVALID_SOCKET){SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), RED);perror("Accept failed\n");SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);continue;}//если подключение установлено, то создается новый сокет
        handle_client(client_socket);
    }
    closesocket(server_socket);
    WSACleanup();
    return 0;
}


char *read_html_file(const char *filename){

    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), YELLOW);//Меняем цвет на желтый
    printf("Opening file: %s\n", filename);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);//Меняем цвет на белый

    FILE *file = fopen(filename, "r");//открываем HTML файл
    test_file_error(file);

    fseek(file, 0, SEEK_END);//Перемещаем указатель в конец файла для уточнения его размера
    LONG file_size = ftell(file);
    rewind(file);//Возвращаем указатель в начало файла для чтения

    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), YELLOW);//Меняем цвет на желтый
    printf("File size: %ld bytes\n", file_size);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);//Меняем цвет на белый

    char *content = (char*)malloc(file_size + 1);//Выделяем память под контент страницы
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), YELLOW);//Меняем цвет на желтый
    printf("Memory got: %zu bytes\n", sizeof(content));
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);//Меняем цвет на белый

    test_content_error(content, file);

    size_t bytes_read = fread(content, 1, file_size, file);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), YELLOW);//Меняем цвет на желтый
    printf("Bytes read from file: %zu\n", bytes_read);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);//Меняем цвет на белый

    test_bytes_read_error(bytes_read, file_size, file, content);

    content[file_size] = '\0';
    fclose(file);
    return content;
}

void handle_client(SOCKET client_socket){
    char buffer[BUFFER_SIZE];//Буфер приема и отправки информации
    int recived = recv(client_socket, buffer, BUFFER_SIZE - 1, 0); //Получает информацию от сервера
    test_recive_error(recived);

    buffer[recived] = '\0';//Задаем конец строки в буфере
    printf("Recived request: \n%s\n", buffer);

    if(strstr(buffer, "GET /favicon.ico") != 0){ //Проверка на наличие фавикона в GET запросе. Если его нет, то отдает страницу без него
        char *error_response = "HTTP/1.1 404 Not Found\r\n\r\n";
        send(client_socket, error_response, (int)strlen(error_response), 0);
    }
    else if((strstr(buffer, "GET /") != 0)){//Обработка GET запросов
        char *html_content = read_html_file("D:\\Projects\\C\\http_server\\src\\temp.html");//Получаем контент из функции
        test_html_content_error(html_content);


        size_t response_size = strlen(html_content) + BUFFER_SIZE;
        char *http_response = (char*)malloc(response_size); //Задаем размер массива
        test_http_response_error(http_response, client_socket, html_content);

        snprintf(http_response, response_size,
            "HTTP/1.1 200 OK\r\n"
            "Content-Type: text/html; charset=utf-8\r\n"
            "Content-Length: %zu\r\n"
            "\r\n"
            "%s", 
            strlen(html_content), html_content); 
            

        send(client_socket, http_response, (int)strlen(http_response), 0);//отправляем информацию клиенту
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), GREEN);//Меняем цвет на зеленный
        printf("Succsessfully sent GET data!\n");
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);//Меняем цвет на белый
        printf("------------------------------------------------------------------------------------------------\n");
        closesocket(client_socket);
        free(html_content);
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);//Меняем цвет на белый
    }
    else if(strstr(buffer, "POST /") != NULL){//Обработка POST запросов
        char *body = strstr(buffer, "\r\n\r\n");
        if(body != NULL){
            body += 4; //Пропускаем пустую строку

            //Парсинг данных application/x-www-form-urlencoded
            char *key, *value, *saveptr;
            key = strtok_s(body, "=&", &saveptr);
            while(key != NULL){
                value = strtok_s(NULL, "=&", &saveptr);
                printf("Key: %s, Value: %s\n", key,value);
                key = strtok_s(NULL, "=&", &saveptr);
            }
        }
        char *post_response = "HTTP/1.1 200 OK\r\n\r\n";

        send(client_socket, post_response, (int)strlen(post_response), 0);//отправляем данные через сокет клиенту
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), GREEN);//Меняем цвет на зеленный
        printf("Succsessfully sent POST data!\n");
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);//Меняем цвет на белый
        printf("------------------------------------------------------------------------------------------------\n");
        closesocket(client_socket);
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);//Меняем цвет на белый   
    }
}