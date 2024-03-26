// app.sps

// Nest.js 모듈 불러오기
import { Module, Controller, Get } from "@nestjs/common";

// Nest.js에서 사용할 모듈 정의
@Module({
  controllers: [AppController],
})
class AppModule {}

// 컨트롤러 정의
@Controller()
class AppController {
  constructor() {}

  // GET 요청에 대한 핸들러 정의
  @Get()
  getData() {
    return "Hello from Nest.js!";
  }
}
