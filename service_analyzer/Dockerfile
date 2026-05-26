FROM ubuntu:22.04

RUN apt-get update && apt-get install -y \
    build-essential \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /app

# Просто копируем уже созданные вами файлы из папки прямо в контейнер
COPY httplib.h .
COPY main.cpp .

# Компиляция кода с поддержкой стандарта C++14 и потоков
RUN g++ -std=c++14 main.cpp -I. -pthread -o analyzer

EXPOSE 8080
CMD ["./analyzer"]
