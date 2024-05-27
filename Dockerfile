# Установка базового образа Alt Linux
FROM alt:latest
# Установка необходимых пакетов для QT
RUN apt-get update && apt-get install -y \
    gcc \
    build-essential\
    qtcreator\
    cmake\
    wine

WORKDIR /KR
COPY . /KR
# WORKDIR /QT
# COPY . 
RUN cmake .
ENV DISPLAY=host.docker.internal:0
# Установка команды запуска QT проекта
CMD  ["./KR/build-Security_pattern-Desktop_Qt_6_6_2_MinGW_64_bit-Release/Security_pattern.exe"]


