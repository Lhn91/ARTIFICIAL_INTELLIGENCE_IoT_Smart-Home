const sensorService = require('../services/sensors.service');

exports.createSensorData = async (req, res) => {
    try {
      const sensor_data = await sensorService.createSensorData(req.body);
      res.status(200).json(sensor_data);
    } catch (error) {
      res.status(500).json({ message: error.message });
    }
  
  };

  exports.getAllSensorData = async (req, res) => {
    try {
      const sensors_data = await sensorService.getAllSensorData();
      console.log("gett")
      res.status(200).json(sensors_data);
    } catch (error) {
      res.status(500).json({ message: error.message });
    }
  };


  exports.getSensorDataWithinRange = async (req, res) => {
    try {
      const sensors_data = await sensorService.getSensorDataWithinRange(req.body);
      res.status(200).json(sensors_data);
    } catch (error) {
      res.status(500).json({ message: error.message });
    }
  };



  exports.getSensorDataById = async (req, res) => {
    try {
      const sensor_data = await sensorService.getSensorDataById(req.params.id);
      if (!sensor_data) {
        return res.status(404).json({ message: 'Sensor data not found' });
      }
      res.status(200).json(sensor_data);
    } catch (error) {
      res.status(500).json({ message: error.message });
    }
  };



exports.deleteSensorData = async (req, res) => {
    try {
      const sensor_data = await sensorService.deleteSensorData(req.params.id);
      res.status(200).json(sensor_data);
    } catch (error) {
      res.status(500).json({ message: error.message });
    }
  };

