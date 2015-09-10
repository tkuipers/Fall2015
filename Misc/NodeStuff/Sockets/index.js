'use strict';

var http = require('http');
var express = require('express');
var bodyParser = require('body-parser');
var path = require('path');
var config = require("config");
var logger = require("tracer").colorConsole();
var app = express();


var server = http.createServer(app);
module.exports = {
	body: function(){
		app.use(bodyParser.json());
	},
	//---------------------------------------ADDEDLINES--------------------------------------
	// app.set('view engine', 'jade');
	// app.set('views', path.join(__dirname, 'frontend/views'));
	// app.locals.pretty = true;
	// app.use(express.static(process.cwd() + '/frontend'));
	// app.use(function(req, res, next) {
		// res.header("Access-Control-Allow-Origin", "*");
		// res.header("Access-Control-Allow-Headers", "Origin, X-Requested-With, Content-Type, Accept");
		// next();
	// });
	// app.get("/config", function(req, res){
		// res.sendFile(path.join(__dirname, 'config/RVA.json'));
	// });
	// app.get("/clientConfig", function(req, res){
		// res.sendFile(path.join(__dirname, 'config/clientConfig.js'));
	// });
	// app.get('/story/:storyId', function (req, res) {
		// res.render('storyOverview.jade', { storyId: req.params.storyId});
	// });
	// app.get('/viewstory/:storyId', function (req, res) {
		// res.render('storyView.jade', { storyId: req.params.storyId});
	// });
	// app.get('/editstory/:storyId', function (req, res) {
		// res.render('storyEdit.jade', { storyId: req.params.storyId});
	// });
	// app.get('/editatlas', function (req, res){
		// res.render('editAtlas.jade', {atlasTitle: config.get("clientSide.atlasTitle")});
	// });
	// app.get('/', function (req, res) {
		// res.render('index.jade', {atlasTitle: config.get("clientSide.atlasTitle")});
	// });
	//---------------------------------------------------------------------------------------
	// app.get('/api', function (req, res) {
		// res.status(200).send();
	// });
	
	// app.use(swaggerize({
		// api: path.resolve('./config/RVA.yaml'),
		// handlers: path.resolve('./handlers')
	// }));
	
	listen: function(){
		server.listen(config.get("serverConfig.port"), function () {
			app.setHost(server.address().address + ':' + server.address().port);
			logger.info("Listening on port 0.0.0.0:" + config.get("serverConfig.port"));
		});
	}
}
