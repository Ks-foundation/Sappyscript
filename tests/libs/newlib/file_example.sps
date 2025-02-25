import "sps_lib.sps";

// 파일 쓰기
FileSystem.writeFile("example.txt", "Hello, Sappyscript!");

// 파일 읽기
var(content, FileSystem.readFile("example.txt"));
log("파일 내용: %s", content);
