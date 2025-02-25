import "fs";

// 템플릿 파일을 읽고 변환하는 함수
function renderTemplate(filename, data) {
    var(template, fs.readFileSync(filename, "utf-8"));

    // include 기능 지원
    template = template.replace(/{% include \"(.*?)\" %}/g, function(match, filename) {
        return fs.readFileSync(filename, "utf-8");
    });

    // 변수 치환 ({{ 변수명 }} → 값)
    template = template.replace(/\{\{ (.*?) \}\}/g, function(match, p1) {
        return (data[p1] ? data[p1] : "");
    });

    // if 조건문 처리
    template = template.replace(/{% if (.*?) %}([\s\S]*?){% endif %}/g, function(match, condition, content) {
        if (data[condition] == true) {
            return content;
        }
        return "";
    });

    // for 루프 처리
    template = template.replace(/{% for (.*?) in (.*?) %}([\s\S]*?){% endfor %}/g, function(match, varName, listName, content) {
        var(output, "");
        if (data[listName]) {
            data[listName].forEach(function(item) {
                var(localData, { ...data });
                localData[varName] = item;
                output += content.replace(/\{\{ (.*?) \}\}/g, function(m, v) {
                    return localData[v] ? localData[v] : "";
                });
            });
        }
        return output;
    });

    return template;
}

// 템플릿을 렌더링하여 HTML로 저장하는 함수
function renderToFile(templateFile, outputFile, data) {
    var(result, renderTemplate(templateFile, data));
    fs.writeFileSync(outputFile, result, "utf-8");
}
