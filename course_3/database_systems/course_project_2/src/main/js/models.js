var mongoose = require("mongoose");

var UserSchema = mongoose.Schema({
    name: { type: String, required: true },
    photo: { type: Buffer },
    money_amount: { type: Number, min: 0, required: true },
    phone: { 
        type: String, 
        validate: { 
            validator: function(phone) {
                return /\d{3}-\d{3}-\d{2}-\d{2}/.test(phone);
            }, 
            message: "Phone is not in correct format. Try like so: '918-333-12-34'" 
        }, 
        required: true 
    },
    friends: { type: [ mongoose.Schema.Types.ObjectId ], ref: 'User'},
    is_admin: { type: Boolean, required: true },
    pet: { type: mongoose.Schema.Types.ObjectId, ref: 'Pet' }
});

var PetSchema = mongoose.Schema({
    name: { type: String, required: true },
    user: { type: mongoose.Schema.Types.ObjectId, ref: 'User', required: true },
    species: { type: mongoose.Schema.Types.ObjectId, ref: 'Species', required: true },
    birth_date: { type: Date, required: true, default: Date.now },
    death_date: { type: Date, required: true },
    happiness: { type: Number, min: 0, max: 10, required: true },
    hungriness: { type: Number, min: 0, max: 10, required: true },
    illness: { type: Number, min: 0, max: 10, required: true }
});

var SpeciesSchema = mongoose.Schema({
    name: { type: String, required: true },
    texture: { type: Buffer, required: true }
});

var FoodSchema = mongoose.Schema({
    name: { type: String, required: true },
    satiety: { type: Number, min: 0, max: 10, required: true }
});

var EntertainmentsSchema = mongoose.Schema({
    name: { type: String, required: true },
    quality: { type: Number, min: 0, max: 10, required: true }
});

var ScoreboardSchema = mongoose.Schema({
    user: { type: mongoose.Schema.Types.ObjectId, ref: 'User', required: true },
    rank: { type: Number, min: 0, required: true }
});

module.exports = {
    User: mongoose.model('User', UserSchema),
    Pet: mongoose.model('Pet', PetSchema),
    Species: mongoose.model('Species', SpeciesSchema),
    Food: mongoose.model('Food', FoodSchema),
    Entertainments: mongoose.model('Entertainments', EntertainmentsSchema),
    Scoreboard: mongoose.model('Scoreboard', ScoreboardSchema)
}
