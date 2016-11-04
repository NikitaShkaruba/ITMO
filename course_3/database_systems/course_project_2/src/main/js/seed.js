var models = require('./models.js');
var mongoose = require('mongoose');
mongoose.connect('mongodb://localhost/course_project_2_db');
var db = mongoose.connection;

function saveToDbCallback(error) {
    if (error)
        console.log(error);
    else
        console.log('Saved instance');
}

// Register callback if db connection fails
db.on('error', console.error.bind(console, 'connection error:'));

// Register callback if db connection successfull
db.once('open', function() {
    var mikey = new models.Pet({
        name: "Mikey",
        species: "Dog",
        birth_date: Date.now(),
        death_date: Date.now() + 7,
        happiness: 3,
        hungriness: 0,
        illness: 0
    });
    mikey.save(saveToDbCallback); 
});
