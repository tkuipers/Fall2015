'use strict';

var Sockets = require('../lib/Sockets.js');

/*
	======== A Handy Little Nodeunit Reference ========
	https://github.com/caolan/nodeunit

	Test methods:
		test.expect(numAssertions)
		test.done()
	Test assertions:
		test.ok(value, [message])
		test.equal(actual, expected, [message])
		test.notEqual(actual, expected, [message])
		test.deepEqual(actual, expected, [message])
		test.notDeepEqual(actual, expected, [message])
		test.strictEqual(actual, expected, [message])
		test.notStrictEqual(actual, expected, [message])
		test.throws(block, [error], [message])
		test.doesNotThrow(block, [error], [message])
		test.ifError(value)
*/

exports['awesome'] = {
	setUp: function(done) {
		// setup here
		done();
	},
	'no args': function(test) {
		test.expect(1);
		// tests here
		test.equal(Sockets.awesome(), 'awesome', 'should be awesome.');
		
		test.done();
	},
	'args': function(test){
		var out = "hello";
		test.equal(Sockets.cool(out), out, "IT WORKS");
		test.done();
	},
	'classArgs': function(test){
		var other = "hey";
		var out = {
			'val': other
		};
		test.equal(Sockets.better(out), other, "YAY");
		test.done();
	}
};
