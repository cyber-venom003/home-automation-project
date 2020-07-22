var express = require('express');
var app = express();

var sampleJSON = {
    name: 'Tejas Agrawal',
    field: 'ECE',
    
}

app.get('/' , (req , res) => {
    res.json(sampleJSON);
});

app.listen(3000 , '192.168.43.253' , () => {
    console.log('Server listening on port 3000');
});