const sensorModel = require('../models/sensors.model');

exports.getAllSensorData = async () => {
    try {
        return await sensorModel.getAllSensorData();
    } catch(err){
        throw new Error(err);
    }
};

exports.getSensorDataById = async (id) => {
    try {
        return await sensorModel.getSensorDataById(id);
    } catch(err){
        throw new Error(err);
    }
};

exports.getSensorDataWithinRange = async (time) => {
    try {
        return await sensorModel.getSensorDataWithinRange(time);
    } catch(err){
        throw new Error(err);
    }
};

exports.createSensorData = async (data) => {
    try {
        return await sensorModel.createSensorData(data);
    } catch(err){
        throw new Error(err);
    }
};

exports.deleteSensorData = async (id) => {
    try {
      return await sensorModel.deleteSensorData(id);
    } catch (err) {
      throw new Error(err);
    }
  };
