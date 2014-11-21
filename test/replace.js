var assert = require('assert');
var RE2 = require('../index');

var replace = [
    {
        regex: 'b+',
        replace: '',
        cases: {
            'abc': 'ac',
            'abbbbbc': 'ac',
            'abbaba': 'aaba',
            'cde': 'cde'
        }
    },
    {
        regex: '[a-z0-9]{2,4}',
        replace: '*',
        cases: {
            '  a039 12345 1 34': '  * 12345 1 34',
            '15.043': '*.043'
        }
    },
    {
        regex: '^\/foo',
        replace: '/bar',
        cases: {
            '/foo/baz': '/bar/baz',
            '/x/foo': '/x/foo'
        }
    }
];

describe('RE2', function () {
    describe('#replace', function () {
        replace.forEach(function (test) {
            var re = new RE2(test.regex);

            Object.keys(test.cases).forEach(function (input) {
                var output = test.cases[input];

                it('should replace ' + input + ' with ' + output +
                        ' for s/' + test.regex + '/' + test.replace + '/', function () {

                    assert.equal(re.replace(input, test.replace), output);
                });
            });
        });
    });
});
