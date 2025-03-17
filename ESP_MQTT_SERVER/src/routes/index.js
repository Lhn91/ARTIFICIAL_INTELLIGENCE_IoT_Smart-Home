const express = require('express');
const router = express.Router();

const sensorRoutes = require('./sensors.route');

// use the routes as middle
router.use('/sensor', sensorRoutes);

module.exports = router;