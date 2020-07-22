var express = require('express');
var app = express();

var sampleJSON = {
    name: 'Tejas Agrawal',
    field: 'ECE',
    hobbies: {
        games: ['COD' , 'Prototype Series'],
        softD: ['WebD' , 'AppD' , 'Backend' , 'IoT']
    }
}

app.get('/' , (req , res) => {
    res.json(sampleJSON);
});

app.listen(3000 , () => {
    console.log('Server listening on port 3000');
});