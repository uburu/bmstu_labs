var Ajv = require('ajv');
var ajv = new Ajv({allErrors: true});

var fs = require('fs');


var schema = {
  "properties": {
    "id": { "type": "number" },
    "name": { "type": "string" },
    "email": { "type": "string" },
    "adress": { "type": "string" },
    "Games": { "type": "array",
                "items": [
                  { "id": "number" },
                  { "name": { "type": "string" } },
                  { "platform": { "type": "string" } },
                  { "genre": { "type": "string" } },
                  { "release_year": { "type": "number" } },
                  { "developer_id": { "type": "number" } },
                ] 
              }
  }
};


var data = {
    "id":1,
    "name":"Nintendo",
    "email":"erin24@nintendo.org",
    "adress":"17618 Newton Harbor Juanview, CO 39066",
    "Games":[{
        "id":1,
        "name":"Wii Sports",
        "platform":"Wii",
        "genre":"Sports",
        "release_year":2006,
        "developer_id":1
    },
    {
        "id":2,
        "name":"Super Mario Bros.",
        "platform":"NES",
        "genre":"Platform",
        "release_year":1985,
        "developer_id":1
    },
    {"id":3,"name":"Mario Kart Wii","platform":"Wii","genre":"Racing","release_year":2008,"developer_id":1}
    ]
}

var dataFromFile = '';

fs.readFile('data.json', 'utf8', function(err, contents) {
  dataFromFile = contents;
});


var validate = ajv.compile(schema);

test(data);
test(dataFromFile);

function test(data) {
  var valid = validate(data);
  if (valid) console.log('Valid!');
  else console.log('Invalid: ' + ajv.errorsText(validate.errors));
}
