<h1>HTTP Server in C</h1>
<h2>Описание</h2>
<p>Этот проект представляет собой простой HTTP-сервер, написанный на языке C. Сервер обрабатывает запросы GET и POST, отвечает с содержимым HTML-файлов и может выводить данные в консоль с различными цветами в зависимости от состояния работы.</p>
<h2>Требования</h2>
<ul>
  <li>Windows</li>
  <li>Компилятор C (например, GCC или MSVC)</li>
  <li>WinSock2 библиотека</li>
</ul>
<h2>Установка и запуск</h2>
<ol>
  <li>Клонируйте репозиторий:
    <pre><code>git clone https://github.com/yourusername/yourrepository.git
cd yourrepository</code></pre>
  </li>
  <li>Скомпилируйте проект:
    <pre><code>gcc -Iincludes -Isrc -Itests includes/includes.h src/main.c src/server.h tests/tests.c tests/tests.h -o main -lws2_32</code></pre>
  </li>
  <li>Запустите сервер:
    <pre><code>./main</code></pre>
  </li>
</ol>
<h2>Использование</h2>
<ol>
  <li>При запуске сервер попросит ввести номер порта:
    <pre><code>Enter the port number: 8080</code></pre>
  </li>
  <li>Сервер начнет прослушивание указанного порта и будет ожидать подключения клиентов.</li>
</ol>
<h2>Функциональность</h2>
<ul>
  <li><strong>GET-запросы:</strong> Возвращает содержимое HTML-файла.</li>
  <li><strong>POST-запросы:</strong> Обрабатывает данные, закодированные в формате <code>application/x-www-form-urlencoded</code>.</li>
</ul>
<h2>Пример запроса</h2>
<ul>
  <li><strong>GET:</strong>
    <pre><code>curl http://localhost:8080/</code></pre>
  </li>
  <li><strong>POST:</strong>
    <pre><code>curl -X POST -d "key1=value1&key2=value2" http://localhost:8080/</code></pre>
  </li>
</ul>
<h2>Файловая структура</h2>
<ul>
  <li><code>server.c</code>: Основной файл с реализацией сервера.</li>
  <li><code>server.h</code>: Заголовочный файл с объявлениями функций.</li>
  <li><code>tests.h</code>: Заголовочный файл с функциями для тестирования ошибок.</li>
  <li><code>includes.h</code>: Заголовочный файл с подключением необходимых библиотек и объявлением цветов.</li>
</ul>
<h2>Функции и тесты</h2>
<h3>Основные функции</h3>
<ul>
  <li><code>main()</code>: Основная функция, запускающая сервер и обрабатывающая подключения.</li>
  <li><code>handle_client(SOCKET client_socket)</code>: Обрабатывает запросы от клиента.</li>
  <li><code>read_html_file(const char *filename)</code>: Читает HTML-файл и возвращает его содержимое.</li>
</ul>
<h3>Тестовые функции</h3>
<ul>
  <li><code>test_WSAStartup_error(WSADATA wsadata)</code>: Тестирует ошибки инициализации WinSock.</li>
  <li><code>test_socket_error(int server_socket)</code>: Тестирует ошибки создания сокета.</li>
  <li><code>test_bind_error(int server_socket, struct sockaddr_in server_addr)</code>: Тестирует ошибки привязки сокета.</li>
  <li><code>test_listen_error(int server_socket)</code>: Тестирует ошибки начала прослушивания сокета.</li>
  <li><code>test_file_error(FILE *file)</code>: Тестирует ошибки открытия файла.</li>
  <li><code>test_content_error(char *content, FILE *file)</code>: Тестирует ошибки выделения памяти для содержимого файла.</li>
  <li><code>test_bytes_read_error(size_t bytes_read, LONG file_size, FILE *file, char *content)</code>: Тестирует ошибки чтения файла.</li>
  <li><code>test_recive_error(int recive)</code>: Тестирует ошибки получения данных от клиента.</li>
  <li><code>test_html_content_error(char *html_content)</code>: Тестирует ошибки чтения содержимого HTML.</li>
  <li><code>test_http_response_error(char *http_response, SOCKET client_socket, char *html_content)</code>: Тестирует ошибки выделения памяти для HTTP-ответа.</li>
</ul>

<h2>Лицензия</h2>
<p>Этот проект лицензирован под лицензией MIT.</p>