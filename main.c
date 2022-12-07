#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 
#include <curl/curl.h>
#include "json.h"
 
struct MemoryStruct {
  char *memory;
  size_t size;
};
 
static size_t
WriteMemoryCallback(void *contents, size_t size, size_t nmemb, void *userp)
{
  size_t realsize = size * nmemb;
  struct MemoryStruct *mem = (struct MemoryStruct *)userp;
 
  char *ptr = realloc(mem->memory, mem->size + realsize + 1);
  if(!ptr) {
    /* out of memory! */
    printf("not enough memory (realloc returned NULL)\n");
    return 0;
  }
 
  mem->memory = ptr;
  memcpy(&(mem->memory[mem->size]), contents, realsize);
  mem->size += realsize;
  mem->memory[mem->size] = 0;
 
  return realsize;
}
 
int main(int argc, char** argv)
{
  char *UrlAdrsHead = "https://wttr.in/";
  char *UrlAdrsTail = "?format=j1&lang=ru";
  char *UrlAdrs;

  CURL *curl_handle;
  CURLcode res;

  json_char* json;
  json_value* value;
  json_value* ValWeather;
 
  struct MemoryStruct chunk;

  if (argc != 2) 
  {
    fprintf(stderr, "Введите имя программы и название города\n");
    return 1;
  }

  UrlAdrs = (char *)calloc((strlen(UrlAdrsHead) + strlen(argv[1]) + strlen(UrlAdrsTail) + 1), sizeof(char));
  if(!UrlAdrs) 
  {
    printf ("Возникла ошибка привыделении памяти. Программа будет остановлена");
    exit (1);
  }
 
  UrlAdrs = strcat(UrlAdrs, UrlAdrsHead);
  UrlAdrs = strcat(UrlAdrs, argv[1]);
  UrlAdrs = strcat(UrlAdrs, UrlAdrsTail);
  
  chunk.memory = NULL;  /* will be grown as needed by the realloc above */
  chunk.size = 0;    /* no data at this point */
 
  curl_global_init(CURL_GLOBAL_ALL);
 
  /* init the curl session */
  curl_handle = curl_easy_init();
 
  /* specify URL to get */
  curl_easy_setopt(curl_handle, CURLOPT_URL, UrlAdrs);

  free(UrlAdrs);
 
  /* send all data to this function  */
  curl_easy_setopt(curl_handle, CURLOPT_WRITEFUNCTION, WriteMemoryCallback);
 
  /* we pass our 'chunk' struct to the callback function */
  curl_easy_setopt(curl_handle, CURLOPT_WRITEDATA, (void *)&chunk);
 
  /* some servers do not like requests that are made without a user-agent
     field, so we provide one */
  curl_easy_setopt(curl_handle, CURLOPT_USERAGENT, "libcurl-agent/1.0");
 
  /* get it! */
  res = curl_easy_perform(curl_handle);
 
  /* check for errors */
  if(res != CURLE_OK) 
  {
    fprintf(stderr, "curl_easy_perform() failed: %s\n",
            curl_easy_strerror(res));
  }
  else {
        
        json = (json_char*)chunk.memory;

        value = json_parse(json,chunk.size);

        if (value == NULL) {
          fprintf(stderr, "Unable to parse data\n");
           exit(1);
        }

        //Вытаскиваем необходимую информацию из объединений
        ValWeather = value->
                     u.object.values[3].value ->       // Weather
                     u.array.values[0];                // array[0] = текущий день      

        if(strcmp(ValWeather -> u.object.values[3].name, "date") || (ValWeather -> u.object.values[3].value -> type != json_string))
        {
          printf("Json content formatting error\n");
          return 0;
        }
        else printf("Прогноз погоды на %s 12 ч 00 м:\n", ValWeather -> u.object.values[3].value -> u.string.ptr);

        ValWeather = value ->
                     u.object.values[3].value ->       // Weather
                     u.array.values[0] ->              // array[0] = текущий день      
                     u.object.values[4].value ->       // hourly
                     u.array.values[4] ->              // array[4] = 12 часов
                     u.object.values[22].value ->      // lang_ru
                     u.array.values[0];               // array[0]
        if(strcmp(ValWeather -> u.object.values[0].name, "value") || (ValWeather -> u.object.values[0].value -> type != json_string))
        {
          printf("Json content formatting error\n");
          return 0;
        }
        else printf("%s\n", ValWeather -> u.object.values[0].value -> u.string.ptr);

        ValWeather = value->
                     u.object.values[3].value ->       // Weather
                     u.array.values[0] ->              // array[0] = текущий день      
                     u.object.values[4].value ->       // hourly
                     u.array.values[4];                // array[4] = 12 часов
        if(strcmp(ValWeather -> u.object.values[36].name, "winddir16Point") || (ValWeather -> u.object.values[36].value -> type != json_string))
        {
          printf("Json content formatting error\n");
          return 0;
        }
        else printf("Направление ветра: %s\n", ValWeather -> u.object.values[36].value -> u.string.ptr); // направление ветра
        
        if(strcmp(ValWeather -> u.object.values[38].name, "windspeedKmph") || (ValWeather -> u.object.values[38].value -> type != json_string))
        {
          printf("Json content formatting error\n");
          return 0;
        }
        else printf("Скорость ветра: %s км/ч ", ValWeather -> u.object.values[38].value -> u.string.ptr);
                                   
        if(strcmp(ValWeather -> u.object.values[8].name, "WindGustKmph") || (ValWeather -> u.object.values[8].value -> type != json_string))
        {
          printf("Json content formatting error\n");
          return 0;
        }
        else printf("с порывами до %s км/ч\n", ValWeather -> u.object.values[8].value -> u.string.ptr); 

        if(strcmp(ValWeather -> u.object.values[27].name, "tempC") || (ValWeather -> u.object.values[27].value -> type != json_string))
        {
          printf("Json content formatting error\n");
          return 0;
        }
        else printf("Температура воздуха: %s °C, ", ValWeather -> u.object.values[27].value -> u.string.ptr); 
        
        if(strcmp(ValWeather -> u.object.values[6].name, "tempC") || (ValWeather -> u.object.values[6].value -> type != json_string))
        {
          printf("Json content formatting error\n");
          return 0;
        }
        else printf("ощущается как %s °C\n", ValWeather -> u.object.values[6].value -> u.string.ptr); 
        

        json_value_free(value);
  }
 
  /* cleanup curl stuff */
  curl_easy_cleanup(curl_handle);
 
  free(chunk.memory);
 
  /* we are done with libcurl, so clean it up */
  curl_global_cleanup();
 
  return 0;
}