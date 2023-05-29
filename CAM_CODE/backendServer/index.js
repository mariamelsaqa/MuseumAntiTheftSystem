// More libraries (you need to import express in every file you use it)

import fetch from "node-fetch";
import express from "express";
import morgan from "morgan";
import fs from "fs";

const port = 3000;
const app = express();

// This sets the access control headers for this server.
// Unless you 100% know what you're doing, use these as-is.
// --
// Do note you should almost never use "Access-Control-Allow-Origin", "*"
// in actual development.
app.use(function (req, res, next) {
  res.setHeader("Access-Control-Allow-Origin", "*");
  res.setHeader("Access-Control-Allow-Credentials", "true");
  res.setHeader("Access-Control-Allow-Methods", "GET,HEAD,OPTIONS,POST,PUT");
  res.setHeader(
    "Access-Control-Allow-Headers",
    "Access-Control-Allow-Headers, Origin,Accept, X-Requested-With, Content-Type, Access-Control-Request-Method, Access-Control-Request-Headers"
  );
  next();
});

// This adds the logger.
app.use(morgan(":method :url :status - :response-time ms"));

// Mapping the routes from ./routes to "/"
// You could also map them to /myroutes for example:
// -- app.use("/myroutes", routes);
// -- So instead of localhost:3000/ok, it would be localhost:3000/myroutes/ok

// Start running the server on 10.40.229.164
app.listen(port, "192.168.8.103", () => {
  console.log(`Example app listening at http://192.168.8.103:${port}`);
});

// add express.json() middleware
app.use(express.json());

// get request
app.get("/", function (req, res) {
  // make a request to another server
  // to fetch an image
  fetch("http://192.168.8.105:80")
    .then((response) => {
      // save the image to a file
      const dest = fs.createWriteStream("./image.jpg");
      response.body.pipe(dest);
    })
    .catch((err) => {
      // if there is an error, log it
      console.log(err);
    });

  fetch("http://192.168.8.105:80")
    .then((response) => {
      // save the image to a file
      const dest = fs.createWriteStream("./image.jpg");
      response.body.pipe(dest);
    })
    .catch((err) => {
      // if there is an error, log it
      console.log(err);
    });

  res.send("ok");
});
