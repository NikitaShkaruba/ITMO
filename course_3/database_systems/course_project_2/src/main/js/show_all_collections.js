var models = require('./models.js');
var mongoose = require('mongoose');
mongoose.connect('mongodb://localhost/course_project_2_db');
var db = mongoose.connection;

function findInDbCallback(error, result) {
    if (error) 
        console.log(error);
    else { 
        console.log("Found all instabces:");
        console.log(result);
    }
}

// Register callback if db connection fails
db.on('error', console.error.bind(console, 'connection error:'));

// Register callback if db connection successfull
db.once('open', function() {
    // Find all Pet instances
    models.User.find({}, findInDbCallback);
    models.Species.find({}, findInDbCallback);
    models.Pet.find({}, findInDbCallback);
    models.Food.find({}, findInDbCallback);
    models.Entertainments.find({}, findInDbCallback);
    models.Ratings.find({}, findInDbCallback);
});
