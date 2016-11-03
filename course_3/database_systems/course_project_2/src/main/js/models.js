var mongoose = require("mongoose");

// Todo: Add other models: User, Scoreboard, Food, Entertainments, etc

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

module.exports = {
    Pet: mongoose.model('Pet', PetSchema)
}
