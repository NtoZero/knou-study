# pmatrix 스타일 행렬 마크다운 작성 가이드

이 문서는 마크다운 파일 내에서 LaTeX의 `pmatrix`와 유사한 형태로 행렬을 표현하여 가독성을 높이는 방법을 안내합니다.

## 1. 기본 구조

기본적으로 수학적 표현을 지원하는 마크다운 렌더러(GitHub 등)에서 LaTeX 문법을 사용하여 행렬을 표현할 수 있습니다.

```latex
$A = \begin{pmatrix} a & b \\ c & d \end{pmatrix}$
```

위 코드는 다음과 같이 렌더링됩니다.

$A = \begin{pmatrix} a & b \\ c & d \end{pmatrix}$

- `$` 또는 `$$` 기호로 LaTeX 수식 입력을 시작하고 끝냅니다.
- `\begin{pmatrix}`와 `\end{pmatrix}`로 행렬의 시작과 끝을 감쌉니다.
- 행렬의 각 원소는 `&` 기호로 구분합니다.
- 행의 끝은 `\\` 기호로 표시하여 줄을 바꿉니다.

## 2. 예시

### 2x2 행렬
```latex
$A = \begin{pmatrix} 1 & 2 \\ 3 & 4 \end{pmatrix}$
```
$A = \begin{pmatrix} 1 & 2 \\ 3 & 4 \end{pmatrix}$

### 3x3 행렬
```latex
$I_3 = \begin{pmatrix} 1 & 0 & 0 \\ 0 & 1 & 0 \\ 0 & 0 & 1 \end{pmatrix}$
```
$I_3 = \begin{pmatrix} 1 & 0 & 0 \\ 0 & 1 & 0 \\ 0 & 0 & 1 \end{pmatrix}$

### 2x3 행렬
```latex
$B = \begin{pmatrix} 5 & 6 & 7 \\ 8 & 9 & 10 \end{pmatrix}$
```
$B = \begin{pmatrix} 5 & 6 & 7 \\ 8 & 9 & 10 \end{pmatrix}$

## 3. HTML/CSS를 이용한 대체 스타일 (LaTeX 미지원 환경)

일부 마크다운 뷰어는 LaTeX 렌더링을 지원하지 않을 수 있습니다. 이 경우, 인라인 HTML과 CSS를 사용하여 비슷한 효과를 낼 수 있습니다.

### 사용법

문서 상단에 아래와 같은 `<style>` 블록을 추가합니다.

```html
<style>
  table.matrix { border-collapse: collapse; }
  table.matrix td { text-align: center; padding: 5px; }
  table.matrix td:first-child { border-left: 1px solid; padding-left: 8px; }
  table.matrix td:last-child { border-right: 1px solid; padding-right: 8px; }
</style>
```

그 후, `<table>` 태그를 사용하여 행렬을 만듭니다.

```html
<table class="matrix">
  <tr><td>1</td><td>2</td></tr>
  <tr><td>3</td><td>4</td></tr>
</table>
```

### 렌더링 결과

<style>
  table.matrix { border-collapse: collapse; }
  table.matrix td { text-align: center; padding: 5px; }
  table.matrix td:first-child { border-left: 1px solid; padding-left: 8px; }
  table.matrix td:last-child { border-right: 1px solid; padding-right: 8px; }
</style>

<table class="matrix">
  <tr><td>1</td><td>2</td></tr>
  <tr><td>3</td><td>4</td></tr>
</table>

이 방법은 LaTeX보다 코드가 길어지지만, 대부분의 마크다운 환경에서 일관된 출력을 보장하는 장점이 있습니다.
