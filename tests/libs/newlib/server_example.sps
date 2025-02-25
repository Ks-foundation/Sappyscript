import "sps_lib.sps";

// 루트 경로 응답
HTTP.route("get", "/", function(req, res) {
    res.send("Hello, Sappyscript Web Server!");
});

// 서버 실행
HTTP.startServer(3000);
