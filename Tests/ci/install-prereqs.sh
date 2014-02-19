echo "extension=adodb.so" > Extension/adodb.ini
pyrus install pear/PHP_CodeSniffer
phpenv rehash
sudo apt-get -qq install re2c
git clone https://github.com/json-c/json-c
cd json-c
sh autogen.sh 2&>1 /dev/null
./configure --silent
make --silent
sudo make --silent install
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:"/usr/local/lib"
cd ..
composer require phalcon/zephir:dev-master
cd vendor/phalcon/zephir/
./install -c
