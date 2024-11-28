#include <iostream>
#include <curl/curl.h>

// Callback para manejar la respuesta del servidor
size_t WriteCallback(void* contents, size_t size, size_t nmemb, std::string* userp) {
    size_t totalSize = size * nmemb;
    userp->append(static_cast<char*>(contents), totalSize);
    return totalSize;
}

void connectToOrthanc(const std::string& url, const std::string& username = "", const std::string& password = "") {
    CURL* curl;
    CURLcode res;

    curl = curl_easy_init();
    if(curl) {
        std::string responseString;

        // Configuración de la URL
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());

        // Configuración de autenticación básica si es necesaria
        if (!username.empty() && !password.empty()) {
            std::string credentials = username + ":" + password;
            curl_easy_setopt(curl, CURLOPT_USERPWD, credentials.c_str());
        }

        // Callback para manejar la respuesta
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &responseString);

        // Ejecutar la solicitud
        res = curl_easy_perform(curl);

        // Verificar errores
        if (res != CURLE_OK) {
            std::cerr << "Error en la solicitud: " << curl_easy_strerror(res) << std::endl;
        } else {
            std::cout << "Respuesta del servidor:\n" << responseString << std::endl;
        }

        // Limpiar
        curl_easy_cleanup(curl);
    } else {
        std::cerr << "Error inicializando CURL" << std::endl;
    }
}

int main() {
    // URL del servidor Orthanc
    //std::string serverUrl = "http://localhost:8042/";
    std::string serverUrl = "http://raspberry.local:8042/";

    // Usuario y contraseña (si aplica)
    std::string username = "orthanc";
    std::string password = "orthanc";

    // Conectarse al servidor
    connectToOrthanc(serverUrl, username, password);

    return 0;
}
