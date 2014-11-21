var assert = require('assert');
var RE2 = require('../index');

var tests = [
    'b+',
    '[a-z0-9]{2,4}',
    '^/foo',
    'abcdef',
    '((ab)c+)+'
];

describe('RE2', function () {
    describe('.source', function () {
        tests.forEach(function (regex) {
            it('should match source for ' + regex, function () {
                var re = new RE2(regex);
                assert.equal(re.source, regex);
            });
        });
    });
});
