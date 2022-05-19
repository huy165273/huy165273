# Dự án cuối kì lớp học phần INT2215 1 - Lập trình nâng cao

## Nguyễn Ngọc Huy - 21020765

### 1. Hướng dẫn cài đặt:

### 2. Mô tả chung về trò chơi, các ý tưởng chính
#### a) Mô tả chung về trò chơi:
- Tên trò chơi: Dò Mìn

- Cách chơi:
   + Click chuột vào một ô vuông trong bảng. Nếu không may trúng phải ô có mìn (điều này thường xảy ra với người mới chơi) thì trò chơi kết thúc. Trường hợp khác là ô đó không có mìn và một vùng các ô sẽ được mở ra cùng với những con số. Số trên một ô là lượng mìn trong 8 ô nằm quanh với ô đó.
   + Nếu chắc chắn một ô có mìn, người chơi đánh dấu vào ô đó bằng hình lá cờ (click chuột phải).
   + Nếu không chắc chắn một ô có mìn, người chơi đánh dấu vào ô đó bằng hình dấu hỏi chấm (click chuột phải 2 lần).
   + Khi 8 ô lân cận trong một số đã có đủ số mìn mà vẫn còn các ô khác thì những ô đó không có mìn
   + Trò chơi kết thúc với phần thắng dành cho người chơi nếu mở được tất cả các ô không có mìn.
#### b) Các ý tưởng chính
 - Hệ thống bãi mìn của trò chơi dò mìn
 - Hệ thống chọn độ khó
 - Hệ thống âm thanh
 - Hệ thống đồ họa bắt mắt
### 3. Các chức năng được cài đặt trong trò chơi:
- Hiệu ứng âm thanh khi: click chuột, trúng mìn, đặt cờ, chiến thắng , thua cuộc, ...
- Chức năng tắt(mở) âm thanh
- Chọn mức độ khó khi bắt đầu trò chơi (4 mức độ)
- Các chức năng chơi lại, trở về menu, hướng dẫn cách chơi, menu, tương tác với người chơi qua chuột
- Hiển thị thời gian người chơi đang chơi, hiển thị thời gian nhanh nhất người chơi chiến thắng 1 màn chơi
- Video demo [tại đây](https://www.youtube.com/watch?v=8EkawSNiX6k&t=3s)
### 4. Các kỹ thuật lập trình được sử dụng trong chương trình
- Kĩ thuật lập trình đồ họa, âm thanh bằng SDL 
- Kĩ thuật lập trình hướng đối tượng
- Kĩ thuật tách file 
- Các kĩ thuật  khác: Mảng, con trỏ, cấu trúc, lớp, cách tạo số ngẫu nhiên(vị trí ngẫu nhiên), vòng lặp các trạng thái của game, ....
### 5. Kết luận, hướng phát triển và các điều tâm đắc rút ra được sau khi hoàn thiện chương trình
a) Hướng phát triển:
- Làm cho ô đầu tiên người chơi chọn luôn là ô trống (xung quang không có quả mìn nào) để tránh trường hợp người chơi thua luôn ở lần chọn ô đầu tiên.
- Phát triển thêm các tính năng:
  + Tạo thêm nhiều chế độ chơi, có chế độ chơi đặc biệt
  + Tạo chế độ chơi cho người chơi tự cài đặt (số ô vuông theo chiều dài, chiều rộng, số quả mìn)
  + Tạo bản thành tích qua các lần chơi(VD: Thành tích 5 lần chơi thắng nhanh nhất, kèm theo tên người chơi)

b) Điều tâm đắc: 
- Do là Game đầu tay nên vẫn còn nhiều sai sót, code chưa được tối ưu nhất, nhưng qua bài tập này nâng cao trình độ code rất nhiều, qua chương trình rút ra được nhiều kinh nghiệm trong cách làm bài tập lớn để các chương trình sau được hoàn thiện tốt hơn
- Thông qua chương trình học thêm được các kiến thức sau:
  + Biết được tiến trình tạo ra một game và cách vận hành của một game
  + Biết sử dụng SDL 2.0 để tạo một chương trình đồ họa có đồ họa và âm thanh
  + Củng cố kiến thức sử dụng ngôn ngữ lập trình C++
