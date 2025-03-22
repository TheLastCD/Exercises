add daemon to startup:
	sudo cp simpleHello.sh /etc/init.d/
	sudo chmod +x /etc/init.d/simpleHello.sh
	sudo update-rc.d simpleHello.sh defaults


test daemons commands
	sudo service simpleHello.sh start
	sudo service simpleHello.sh stop
	sudo service simpleHello.sh restart
	sudo service simpleHello.sh status



