var models = require('./models.js');
var mongoose = require('mongoose');
mongoose.connect('mongodb://localhost/course_project_2_db');

mongoose.connection.once('connected', () => {
    mongoose.connection.db.dropDatabase();
    console.log('database dropped!');
});
