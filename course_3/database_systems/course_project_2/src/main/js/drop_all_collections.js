var models = require('./models.js');
var mongoose = require('mongoose');
mongoose.connect('mongodb://localhost/course_project_2_db');
var db = mongoose.connection;

// Todo: consider iteration by all exported classes somehow :S
models.Pet.remove({}, function(err) {
    console.log('Collection Pet removed');
});
models.User.remove({}, function(err) {
    console.log('Collection User removed');
});
models.Species.remove({}, function(err) {
    console.log('Collection User removed');
});
