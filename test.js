var RE2 = require('./build/Release/addon');

var re = new RE2('b+');
console.log(re.source);
console.log(re.replace('abbcbd', '*'));
console.log(re.replaceAll('abbcbd', '*'));
