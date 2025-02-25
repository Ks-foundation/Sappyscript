// 기본 모듈 가져오기
import "fs";
import "express";
import "sqlite3";
import "mongodb";
import "react";
import "react-dom";

// 🔹 파일 시스템 기능
namespace FileSystem {
    function readFile(filename) {
        return fs.readFileSync(filename, "utf-8");
    }

    function writeFile(filename, content) {
        fs.writeFileSync(filename, content, "utf-8");
    }
}

// 🔹 HTTP 서버 기능
namespace HTTP {
    var(app, express());

    function startServer(port) {
        app.listen(port, function() {
            log("🚀 Server is running on http://localhost:%s", port);
        });
    }

    function route(method, path, handler) {
        app[method](path, handler);
    }
}

// 🔹 템플릿 엔진 기능
namespace TemplateEngine {
    function render(template, data) {
        return template.replace(/\{\{ (.*?) \}\}/g, function(match, key) {
            return data[key] ? data[key] : "";
        });
    }
}

// 🔹 데이터베이스 기능
namespace Database {
    var(db, new sqlite3.Database("data.db"));

    function query(sql, params, callback) {
        db.all(sql, params, callback);
    }

    function insert(sql, params) {
        db.run(sql, params);
    }
}

// 🔹 유틸리티 기능
namespace Utils {
    function formatDate(date) {
        return new Date(date).toISOString();
    }

    function toUpperCase(str) {
        return str.toUpperCase();
    }
}

// 🔹 React 지원 기능
namespace ReactComponents {
    function createComponent(name, renderFunction) {
        var(component, class extends React.Component {
            constructor(props) {
                super(props);
                this.props = props;
            }
            render() {
                return renderFunction(this.props);
            }
        });
        return component;
    }

    function renderApp(component, containerId) {
        ReactDOM.render(React.createElement(component), document.getElementById(containerId));
    }
}
