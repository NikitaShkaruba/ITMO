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
    var john = new models.User({
        name: "John",
        money_amount: 10000,
        phone: "918-333-22-11",
        is_admin: true
    });
    var shaun = new models.User({
        name: "Shaun",
        money_amount: 0,
        phone: "918-234-12-11",
        is_admin: false
    });
    // Make them friends
    john.friends.push(shaun);
    shaun.friends.push(john);

    var dogSpecies = new models.Species({
        name: "Dog",
        texture: "IMG_RAW_DATA"
    });

    var mikey = new models.Pet({
        name: "Mikey",
        species: dogSpecies,
        user: john,
        birth_date: Date.now(),
        death_date: Date.now() + 7,
        happiness: 3,
        hungriness: 0,
        illness: 0
    });
    john.pet = mikey;

    john.save(saveToDbCallback);
    shaun.save(saveToDbCallback);
    dogSpecies.save(saveToDbCallback);
    mikey.save(saveToDbCallback); 
});
