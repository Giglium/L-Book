FROM ubuntu:trusty

RUN apt-get update -y \
    && apt-get install -y software-properties-common=0.92.37.8 \
    && add-apt-repository --yes ppa:beineri/opt-qt551-trusty \
    && apt-get update -qq \
    && apt-get install -y \
        gcc=4:4.8.2-1ubuntu6 \
        g++=4:4.8.2-1ubuntu6 \
        cmake=2.8.12.2-0ubuntu3 \
        qt55base=5.5.1-1basyskom2 \
        libgl1-mesa-dev=10.1.3-0ubuntu0.6 \
    && rm -rf /var/lib/apt/lists/*

ENV PATH="/opt/qt55/bin:${PATH}"
ENV DISPLAY :0

COPY . /app
WORKDIR /app

RUN qmake && make

CMD ["/app/L-Book"]