#!/usr/bin/env bash


#install apache
apt-get update
apt-get install -y apache2
apt-get install -y tomcat7
if ! [ -L /var/www ]; then
  rm -rf /var/www
  ln -fs /vagrant /var/www
fi

#install Java
apt-get install -y openjdk-7-jdk
