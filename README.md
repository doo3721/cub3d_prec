Cub3d Prectice
=============================

cub3d를 연습하는 레포

텍스쳐를 씌우는 예제를 구현

W,A,S,D: 방향 키

왼쪽, 오른쪽 키 / 마우스 이동: 시점 이동

p: 시점 이동 조작 변경

m: 미니맵 on/off

### TODO
- norm 맞추기


### COMPLETE
- 키 동시입력 구현 (mlx_loop_hook으로 구현, 프레임도 부드러워짐)
- 마우스로 시점 변경 (위와 비슷한 방식으로 구현)
- 동서남북 텍스쳐 구현 (side, step_x, step_y로 구분)
- 모서리 접근시 bus error 버그 수정 (임시 방편으로 이동시 pos_x, pos_y .0으로 딱 떨어지지않게 함)
- 방향키/마우스 시점 변경 선택
- 자잘한 플리커링 없애기 (두 버퍼를 번갈아가면서 출력함으로써 해결)
- minimap 구현 (스크롤링으로 구현)

출처: [365kim - raycasting_tutorial](https://github.com/365kim/raycasting_tutorial)
