FROM debian:jessie
MAINTAINER Denis Follereau <dfollereau@amadeus.com>
COPY . /usr/src/myapp
WORKDIR /usr/src/myapp
RUN apt-get update && apt-get install -y \
    git \
    libxml2-dev \
    python \
    build-essential \
    make \
    gcc \
    python-dev \
    locales \
    python-pip
RUN gcc -o myapp server.c
EXPOSE 8080
ENV PATH /usr/src/myapp:$PATH
CMD ["./myapp"]
