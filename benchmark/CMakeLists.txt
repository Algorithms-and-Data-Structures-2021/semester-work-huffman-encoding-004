# Здесь вы можете создавать свои исполняемые файлы (executables)
# исполянемый файл = контрольный тест

# Пример создания контрольного теста (исполняемого файла) под названием demo_benchmark.
# Исходный код предоставлен в файле demo_benchmark.cpp текущей директории.
add_executable(huffman-encode-benchmark huffman-encode-benchmark.cpp)
add_executable(huffman-decode-benchmark huffman-decode-benchmark.cpp )

# Примечание: Не забываем подключить (прилинковать) библиотеку ${PROJECT_NAME} с реализацией структуры данных.
target_link_libraries(huffman-encode-benchmark PRIVATE project_paths project_warnings ${PROJECT_NAME})
target_link_libraries(huffman-decode-benchmark PRIVATE project_paths project_warnings ${PROJECT_NAME})
