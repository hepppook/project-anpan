Milkcocoa
=====

Milkcocoa client for Node.js.


* v0.0.9

Added onConnected handler at option params.

* v0.0.10

Fixed Error: Connection refused: Server unavailable

* v0.0.13

Fixed reconnect
Added timestamp param callback of on('push') parameter

* v0.0.15

Added timestamp parameter at result of stream.

* v0.0.16

Fixed bug of stream API.


* v0.0.17

Auth reload when ECONNREFUSE Occured

* v0.0.22

Fixed URIError: URI malformed when using "%"


* v0.1.0


Added error callback

'''
ds.push({}, function() {
	//getted server	
}, function(err) {
	//error
});
'''

* v0.4.0

 support node v4

* v0.4.1

git無しでもインストールできるように修正

* v0.5.0

'''
var milkcocoa = new MilkCocoa('app id')
'''
