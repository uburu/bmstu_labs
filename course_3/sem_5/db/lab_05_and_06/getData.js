var fs = require('fs');

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

console.log("Имя разработчика: ", data.name)
data.Games.forEach(element => {
    console.log("Игра: ", element.name)
});

// dataFromFile = JSON.parse(dataFromFile);

// console.log("Имя разработчика: ", dataFromFile.name)
// dataFromFile.Games.forEach(element => {
//     console.log("Игра: ", element.name)
// });


data.newval = "hi"
console.log(data.newval)