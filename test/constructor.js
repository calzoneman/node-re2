var assert = require('assert');
var RE2 = require('../index');

describe('RE2', function () {
    describe('constructor', function () {
        it('should accept a valid regex', function () {
            assert.doesNotThrow(function () {
                new RE2('ab+c');
            });
        });

        it('should raise an error if the regex is invalid', function () {
            assert.throws(function () {
                new RE2('\\d+-(\\d+-\\d+');
            });
        });
    });
});
