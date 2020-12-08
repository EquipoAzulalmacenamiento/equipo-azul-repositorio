'use strict'

const mongoose = require('mongoose')
const Schema = mongoose.Schema

const ProductShema=Schema({
    estado: String,
    temperatura: Number,
    fecha:Date
})

module.exports = mongoose.model('Product', ProductShema)
