const { Pool } = require('pg');
const dbConfig = require ('../config/db.config');

const pool = new Pool({
    user: dbConfig.user,
    host: dbConfig.host,
    database: dbConfig.database,
    password: dbConfig.password,
    port: dbConfig.port
});

pool.on('connect', () => {
    console.log("connected to database");
});

pool.on('error',(err)=>{
    console.log("Unexpected error");
    process.exit(-1);
});

module.exports = pool;