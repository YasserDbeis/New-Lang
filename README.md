# SunLang

# 1. Overview - main / procedural

The main function is the entry point into the program.

### func foo() -> bool {} DOES NOT GIVE AN ERROR

```go
func main() {
  ~ Code Goes Here
  return 0;
}
```

```go
func main() {
  ~ Code Goes Here
}
```

# 2. types

# variables and scoping

# control flow

# output

# functions

# expression (can include operators + left hand blah)

# operators

# errors

## Arithmetic Operators

|      NAME      | SYMBOL |                           DESCRIPTION                           |           EXAMPLE            |
| :------------: | :----: | :-------------------------------------------------------------: | :--------------------------: |
|    Addition    |   +    | Adds two numerical values or concatenates a value with a string | 2 + 3 &#124; "hello " + name |
|  Subtraction   |   -    |           Subtracts one numerical value from another            |           20 - 14            |
| Multiplication |   \*   |                   Multiplies two numerivalues                   |            8 \* 4            |
|    Division    |   /    |            Divides one numerical value from another             |            8 / 4             |

## Comparison Operators

|           NAME           | SYMBOL |                               DESCRIPTION                                | EXAMPLE |
| :----------------------: | :----: | :----------------------------------------------------------------------: | :-----: |
|       Greater than       |   >    |       True if left numerical operand is greater than right operand       | 10 > 5  |
|        Less than         |   <    |        True if left numerical operand is less than right operand         | 20 < 80 |
| Greater than or equal to |   >=   | True if left numerical operand is greater than or equal to right operand | 8 >= 4  |
|  Less than or equal to   |   <=   |  True if left numerical operand is less than or equal to right operand   | 3 <= 5  |
|          Equal           |   is   |              True if left operand is equal to right operand              | 5 is 5  |
|        Not equal         |   !=   |            True if left operand is not equal to right operand            | 5 != 5  |

## Logical Operators

|         NAME         |    SYMBOL    |                      DESCRIPTION                       |         EXAMPLE          |
| :------------------: | :----------: | :----------------------------------------------------: | :----------------------: |
| Logical not (unary)  | not &#124; ! |            Negates right hand boolean value            |  not true &#124; !false  |
|     Logical and      |     and      | Performs logical and operation on two boolean operands | 5 < 10 and "hi" is "bye" |
|      Logical or      |      or      | Performs logical or operation on two boolean operands  | 5 < 10 or "hi" is "bye"  |
| Logical exclusive or |     xor      |     Performs exclusive-or on two boolean operands      |      false xor true      |

## END OF OUR DOCS

## _The Last Markdown Editor, Ever_

[![N|Solid](https://cldup.com/dTxpPi9lDf.thumb.png)](https://nodesource.com/products/nsolid)

[![Build Status](https://travis-ci.org/joemccann/dillinger.svg?branch=master)](https://travis-ci.org/joemccann/dillinger)

Dillinger is a cloud-enabled, mobile-ready, offline-storage compatible,
AngularJS-powered HTML5 Markdown editor.

- Type some Markdown on the left
- See HTML in the right
- ✨Magic ✨

## Features

- Import a HTML file and watch it magically convert to Markdown
- Drag and drop images (requires your Dropbox account be linked)
- Import and save files from GitHub, Dropbox, Google Drive and One Drive
- Drag and drop markdown and HTML files into Dillinger
- Export documents as Markdown, HTML and PDF

Markdown is a lightweight markup language based on the formatting conventions
that people naturally use in email.
As [John Gruber] writes on the [Markdown site][df1]

> The overriding design goal for Markdown's
> formatting syntax is to make it as readable
> as possible. The idea is that a
> Markdown-formatted document should be
> publishable as-is, as plain text, without
> looking like it's been marked up with tags
> or formatting instructions.

This text you see here is \*actually- written in Markdown! To get a feel
for Markdown's syntax, type some text into the left window and
watch the results in the right.

## Tech

Dillinger uses a number of open source projects to work properly:

- [AngularJS] - HTML enhanced for web apps!
- [Ace Editor] - awesome web-based text editor
- [markdown-it] - Markdown parser done right. Fast and easy to extend.
- [Twitter Bootstrap] - great UI boilerplate for modern web apps
- [node.js] - evented I/O for the backend
- [Express] - fast node.js network app framework [@tjholowaychuk]
- [Gulp] - the streaming build system
- [Breakdance](https://breakdance.github.io/breakdance/) - HTML
  to Markdown converter
- [jQuery] - duh

And of course Dillinger itself is open source with a [public repository][dill]
on GitHub.

## Installation

Dillinger requires [Node.js](https://nodejs.org/) v10+ to run.

Install the dependencies and devDependencies and start the server.

```sh
cd dillinger
npm i
node app
```

For production environments...

```sh
npm install --production
NODE_ENV=production node app
```

## Plugins

Dillinger is currently extended with the following plugins.
Instructions on how to use them in your own application are linked below.

| Plugin           | README                                    |
| ---------------- | ----------------------------------------- |
| Dropbox          | [plugins/dropbox/README.md][pldb]         |
| GitHub           | [plugins/github/README.md][plgh]          |
| Google Drive     | [plugins/googledrive/README.md][plgd]     |
| OneDrive         | [plugins/onedrive/README.md][plod]        |
| Medium           | [plugins/medium/README.md][plme]          |
| Google Analytics | [plugins/googleanalytics/README.md][plga] |

## Development

Want to contribute? Great!

Dillinger uses Gulp + Webpack for fast developing.
Make a change in your file and instantaneously see your updates!

Open your favorite Terminal and run these commands.

First Tab:

```sh
node app
```

Second Tab:

```sh
gulp watch
```

(optional) Third:

```sh
karma test
```

#### Building for source

For production release:

```sh
gulp build --prod
```

Generating pre-built zip archives for distribution:

```sh
gulp build dist --prod
```

## Docker

Dillinger is very easy to install and deploy in a Docker container.

By default, the Docker will expose port 8080, so change this within the
Dockerfile if necessary. When ready, simply use the Dockerfile to
build the image.

```sh
cd dillinger
docker build -t <youruser>/dillinger:${package.json.version} .
```

This will create the dillinger image and pull in the necessary dependencies.
Be sure to swap out `${package.json.version}` with the actual
version of Dillinger.

Once done, run the Docker image and map the port to whatever you wish on
your host. In this example, we simply map port 8000 of the host to
port 8080 of the Docker (or whatever port was exposed in the Dockerfile):

```sh
docker run -d -p 8000:8080 --restart=always --cap-add=SYS_ADMIN --name=dillinger <youruser>/dillinger:${package.json.version}
```

> Note: `--capt-add=SYS-ADMIN` is required for PDF rendering.

Verify the deployment by navigating to your server address in
your preferred browser.

```sh
127.0.0.1:8000
```

## License

MIT

**Free Software, Hell Yeah!**

[//]: # "These are reference links used in the body of this note and get stripped out when the markdown processor does its job. There is no need to format nicely because it shouldn't be seen. Thanks SO - http://stackoverflow.com/questions/4823468/store-comments-in-markdown-syntax"
[dill]: https://github.com/joemccann/dillinger
[git-repo-url]: https://github.com/joemccann/dillinger.git
[john gruber]: http://daringfireball.net
[df1]: http://daringfireball.net/projects/markdown/
[markdown-it]: https://github.com/markdown-it/markdown-it
[ace editor]: http://ace.ajax.org
[node.js]: http://nodejs.org
[twitter bootstrap]: http://twitter.github.com/bootstrap/
[jquery]: http://jquery.com
[@tjholowaychuk]: http://twitter.com/tjholowaychuk
[express]: http://expressjs.com
[angularjs]: http://angularjs.org
[gulp]: http://gulpjs.com
[pldb]: https://github.com/joemccann/dillinger/tree/master/plugins/dropbox/README.md
[plgh]: https://github.com/joemccann/dillinger/tree/master/plugins/github/README.md
[plgd]: https://github.com/joemccann/dillinger/tree/master/plugins/googledrive/README.md
[plod]: https://github.com/joemccann/dillinger/tree/master/plugins/onedrive/README.md
[plme]: https://github.com/joemccann/dillinger/tree/master/plugins/medium/README.md
[plga]: https://github.com/RahulHP/dillinger/blob/master/plugins/googleanalytics/README.md
