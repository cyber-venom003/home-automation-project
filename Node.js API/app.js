var express = require('express');
var app = express();
var morgan = require('morgan');
app.use(morgan('combined'));

var sampleJSON = {
    deviceName: 'led',
    status: false, 
}

app.get('/' , (req , res) => {
    res.json(sampleJSON);
});

app.listen(3000 , '192.168.43.253' , () => {
    console.log('Server listening on port 3000');
});