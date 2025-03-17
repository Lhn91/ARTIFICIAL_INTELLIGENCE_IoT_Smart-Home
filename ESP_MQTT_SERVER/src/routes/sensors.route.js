const express = require('express');
const router = express.Router();

const sensorController = require('../controllers/sensors.controller');

router.post('/', sensorController.createSensorData);
router.get('/', sensorController.getAllSensorData);
router.post('/search', sensorController.getSensorDataWithinRange);
router.get('/:id', sensorController.getSensorDataById);
router.delete('/:id', sensorController.deleteSensorData);

module.exports = router;