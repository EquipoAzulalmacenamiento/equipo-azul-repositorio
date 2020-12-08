'use strict'

const express = require('express')
const bodyParser = require('body-parser')
const mongoose = require('mongoose')

const Product = require('./models/product')

const app = express()
const port = process.env.PORT || 3011

app.use(bodyParser.urlencoded({extended: false}))
app.use(bodyParser.json())


mongoose.connect('mongodb://localhost:27017/shop',(err,res)=>{
    if(err) throw err
    console.log('conexion a la base de datos establecida')

    app.listen(port ,() => {
console.log(`API REST corriendo en http://localhost:${port}`)
})
})


app.get('/api/product',(req, res)=>{
    Product.find({}, (err, product) =>{
        if(err) return res.status(500).send({message:`ERROR al realizar la peticion:${err}`})
        if(!product) return res.status(404).send({message:`No existen el producto`})
        
        res.send(200,{product})
        })
})

app.get('/api/product/:productId',(req, res)=>{
    let productId = req.params.productId

    Product.findById(productId, (err, product) =>{
    if(err) return res.status(500).send({message:`ERROR al realizar la peticion:${err}`})
    if(!product) return res.status(404).send({message:`No existen el producto`})
    
    res.status(200).send({product})
    })

})

app.post('/api/product', (req, res)=>{
    console.log('POST /api/product')
    console.log(req.body)
    
    let product = new Product()
    
    product.estado = req.body.estado
    product.temperatura = req.body.temperatura
    product.fecha = Date.now();

    product.save((err, productStored)=>{
        if(err) res.status(500).send({message:`Error al salvar en la base de datos:${err}`})
        
        res.status(200).send({product: productStored})
    })

})
