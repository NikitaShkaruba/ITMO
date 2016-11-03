// Todo: Add other schemas: Users, Ratings, Food, Entertainments...
// Todo: Organize code better. The plan is to create functions for everything and then call them from db.once('open') callback

var mongoose = require('mongoose');
mongoose.connect('mongodb://localhost/course_project_2_db');
var db = mongoose.connection;

db.on('error', console.error.bind(console, 'connection error:'));
db.once('open', function() {
    console.log("0. We're connected");

    // Todo: add player_id: { type: Objectid, required: true },
    var PetSchema = mongoose.Schema({
        name: { type: String, required: true },
        species: { type: String, required: true },
        birth_date: { type: Date, required: true, default: Date.now },
        death_date: { type: Date, required: true },
        happiness: { type: Number, min: 0, max: 10, required: true },
        hungriness: { type: Number, min: 0, max: 10, required: true },
        illness: { type: Number, min: 0, max: 10, required: true }
    });
    console.log("1. Created pet schema");

    var Pet = mongoose.model('Pet', PetSchema);
    console.log("2. Added pet model");

    var mikey = new Pet({
        name: "Mikey",
        species: "Dog",
        birth_date: Date.now(),
        death_date: Date.now() + 4,
        happiness: 3,
        hungriness: 0,
        illness: 0
    });
    console.log("3. Created sample pet");

    mikey.save(function(err) {
        if (err) {
            console.log('!!!!! Error saving sample pet !!!!!');
	    console.log(err);
	} else {
            console.log('4.Saved pet');
	}
    }); 

    // Find all pets
    Pet.find({}, function(err, pets) {
        if (err) 
            throw err;
        else { 
	    console.log("5. Found all pets");
            console.log(pets);
	}
    });
});
