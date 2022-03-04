
[toc]

# CSS基础

## 选择器种类

1. 类型选择器  h1 { }
2. 通配符选择器 * { }
3. 类选择器  .box { }
4. ID选择器  #unique { }
5. 标签属性选择器  a[title] { }
6. 伪类选择器  p:first-child { }
7. 伪元素选择器  p::first-line { }
8. 后代选择器  article p
9. 子代选择器  article > p
10. 相邻兄弟选择器  h1 + p
11. 通用兄弟选择器  h1 ~ p

## 伪类（ Pseudo-classes） VS 伪元素（Pseudo-elements） 
	注： [ˈsjuːdəʊ]    adj.	伪; 假的; 冒充的;

### 概念
#### **伪类 (Pseudo-classes)**   
CSS 伪类 是添加到选择器的关键字，指定要选择的元素的特殊状态。例如，:hover 可被用于在用户将鼠标悬停在按钮上时改变按钮的颜色。  
A CSS pseudo-class is a keyword added to a selector that specifies a special state of the selected element(s).   

#### **伪元素 (Pseudo-elements)**  
> ::after  
> ::before  
> ::cue  
> ::first-letter  
> ::first-line  
> ::file-selector-button  
> ::grammar-error  
> ::marker  
> ::part  
> ::placeholder  
> ::selection  
> ::slotted  
> ::spelling-error  
> ::target-text  

伪元素是一个附加至选择器末的关键词，允许你对被选择元素的特定部分修改样式。下例中的 ::first-line 伪元素可改变段落首行文字的样式。  
A CSS pseudo-element is a keyword added to a selector that lets you style a specific part of the selected element(s). For example, ::first-line can be used to change the font of the first line of a paragraph.
  
 ## CSS盒模型（Box Modal）

+ 组成部分
  + margin 外边距
  + border 边框
  + padding 内边距
  + content 内容

+ 盒模型种类
  + 标准盒模型：width = content
  + IE盒模型：width = content + padding +border

  CSS3中新增box-sizing: content-box | border-box 分别设置盒模型为标准|IE盒模型

  当margin-bottom遇到margin-top时，就会将两个margin距离重叠，保留距离较大的尺寸。要解决这个问题，可以在两个div之间增加一个有高度的元素，如
	<div class="seperator"></div>
	.seperator {
		height: 1px;
	}

 ## float

为解决“绕图排文”诞生，后被用于网页布局，实现左右排版的效果(float和width)
float: left|right
只要有元素开始了float，后续的内容依然会被影响

+ 清除浮动
	1.  clearfix 
   		+ div
			```
			<div class="clearfix"></div>
				.clearfix {
					clear: both;
				}  
			```
        + 使用::after伪类选择器  
			为float内容添加外层div，然后在外层div上添加样式，如  
			```
			.container::after {
				content: '';
				clear: both;
				display: block;
			}
			```
	2. overflow  
				将container的overflow设定为visible以外的任何有效设定值，如auto或者hidden；这时container就会变成一个BFC(Block Formatting Context),中文译作块级可视化上下文，它会形成一个局部的块级，达到"隔断"的效果。  
				```
				.container {
					overflow: auto|hidden;
				}
				```
	  flow-root  
			将container的display设置为flow-root,这也是将.container设定为BFC的另一种方法；但是所有的IE浏览器都不支持  
			```
			.container {
				display: flow-root;
			}
			```

## CSS Position
------------------------------------------
position: static|absolute|relative|fixed|sticky

1. static  
	HTML中所有元素的position默认值都是static; static会跟随HTML排版的流程（flow）移动。static元素对于top、left、right、bottom设定值不生效。  
2. absolute  
	absolute元素会固定在所设定的位置，不会跟随HTML排版的流程移动；但是如果absolute元素索在的容器有scrollbar的话，它就会随scrollbar移动。
	```
	.absolute {
		position: absolute;
		width:200px;
		height:100px;
		right: 80px;
		bottom: 100px;
	}  
	```
3. relative  
	relative和static作用类似，都是会随着HTML的排版流程移动，而它比static多了top、left、right、bottom的设定，即它跟随HTML排版流程去定位之余，还可以再通过top、left、right、bottom去调整位置。
	relative最重要的一个功能是：在它里面的absolute元素会根据relative的位置去定位  
4. fixed  
	fixed和absolute作用类似，不同的地方有两点：
		a)	fixed会定位到荧幕中的固定位置，所以即使卷动页面，也会一直保持在那个位置
		b)	如果fixed有设定top、left、right、bottom的属性，即使放在relative中，fixed也会根据页面，即body去定位，而不会根据relative去定位
		
5. sticky  
	IE所有的浏览器都不支持。
	```
	.sticky {
		position: sticky;
		width: 240px;
		height: 90px;
		top: 0;
	}
	```
	如果页面有纵向scrollbar，sticky会在卷动的过程中，当贴到顶部的时候，固定在顶部；贴到顶部就会固定的原因是我们将它的top设定为0，所以当它的top与上方相距0px的时候就会触发。所以常用于网站的导览。

## 5个常用的CSS单位

1. px   
	绝对单位，1px就是一个光点的大小
	如果文本行距设置为绝对大小，当调整字体大小时，通常也需要同步修改行距
2. em  
	相对单位，是基于目前这个容器的大小设定，再根据em的值去乘出最终的大小
3. rem  
	root em,同em类似，唯一不同的是它是基于root元素，即是html元素的大小设定去计算的。rem同em相比的优势是更容易计算，避免HTML元素在多层嵌套后难以预测元素确实大小的问题。	
4. vw、vh  
	vw viewport width; vh viewport height;
	viewport意思是我们目前看到的这个画面的大小；同其它单位不同，他的设定值只由 *1到100* ，50vw即是画面宽度的一半  
	这个单位最常用的是100vh，将容器占满后，要做水平及垂直居中都会非常容易
5. vmin、vmax  
	vmin代表荧幕较短的一边，而vmax代表荧幕较长的一边，常用于智能设备的旋转屏幕。所以vmin与vmax在配合media query，即是Responsive网页的设定时会很有用

## HTML上下左右居中对齐的三种方法
------------------------------------------
display: inline|inline-block
	将父元素（容器） 设定text-align: center就可实现左右居中
display: block
	将元素本身的margin-left和margin-right设定为auto，就可以左右居中
	
1. position: absolute 【对齐元素本身】  
	首先将元素的position属性设定为absolute，元素就会浮在画面中，然后将left和top属性设置为50%，此时元素的左上点就会处在中心点位置；如果想让整个元素储在中心点位置，可以设定translateX(-50%)与translateY(-50%),就可以达到上下左右居中的效果了
	```
	.center{
		position: absolute;
		top: 50%;
		left: 50%;
		transform: translateX(-50%) translateY(-50%);
	}
	```
2. flexbox 【对齐元素内容】  
	flexbox自带justify-content和align-items两个属性，分别设定主轴和交叉轴的对齐方式。所以只需将两个属性设置为center，元素的内容就会上下左右居中对齐了  
	```
	body{
		min-height: 100vh;
		display: flex;
		justify-content: center;
		align-items: center;
	}
	```
3. diplay: table【对齐元素内容】  
	HTML的table元素有一个valign属性，就是用来设定垂直方向的对齐，而我们可以通过css，将其它元素的display属性设定为table，去将它当作一个table来显示
	```
	body {
		display: table;
		width: 100%;
		min-height: 100vh;
	}
	.cell {
		display: table-cell;
		vertical-align: middle;
		text-align: center;
	}
	```
方法一position absolute是将元素自己于画面中置中，只需要调整元素本身的属性即可；方法二三事先将容器调整成与画面具备相同大小，然后再设定它的内容对齐方式

## Flexbox
#### Flex布局是什么
Flex是Flexible Box的缩写，意为“弹性布局”，是一种用于按行或按列布局元素的 ***一维布局*** 方法用来为盒状模型提供最大的灵活性；  
任何一个容器都可以指定为flex布局  
```
.box {
	display:flex;
}
```   
行内元素也可以使用Flex布局  
```  
.box {
	display: inline-flex;
}  
```  
#### 基本概念
Flex包含两个部分
1. flex container  
   采用flex布局的元素，称为flex container。
2. flex items  
   flex container的所有子元素自动成为容器成员，称为flex items

容器有两根轴：  
1. Main-Axis
   主轴的开始位置叫做 main start
	 主轴结束的位置叫做main end
2. Cross-Axis
   交叉轴开始的位置叫做 cross start
	 交叉轴结束的位置叫做cross end

项目默认沿主轴排列。单个项目占据的主轴空间叫main size,占据的交叉轴空间叫做cross size
#### Flex Container的属性
> flex-direction  
> flex-wrap  
> flex-flow  
> justify-content  
> align-items  
> align-content  

1. flex-direction: row|row-reverse|column|column-reverse  
   设置主轴的方向（即项目排列方向）
2. flex-wrap: nowrap|wrap|wrap-reverse
   默认情况下，项目都在一条线上。flex-wrap定义了如果一条轴线排不下，如何换行:  
		nowrap  (默认)不换行  
		wrap 		 换行，第一行在start方向  
		wrap-reverse  换行，第一行在end方向
3. flex-flow  
   flex-flow是flex-direction属性和flex-wrap属性的简写形式，默认值为row nowrap
4. justify-content: flex-start | flex-end | center | space-between | space-around    
   定义了项目在主轴上的对齐方式
5. align-items: flex-start | flex-end | center | baseline | stretch
   定义了项目在交叉轴上的对齐方式
6. align-content: flex-start | flex-end | center | space-between | space-around  
   This aligns a flex container’s lines within when there is extra space in the cross-axis, similar to how justify-content aligns individual items within the main-axis.
   定义了多根轴线的对齐方式。如果item只有一根轴线，该属性不起作用

#### Flex Items的属性
> order  
> flex-grow  
> flex-shrink  
> flex-basis  
> flex  
> align-self

1. order  
   定义项目的排列顺序。数值越小，排列越靠前，默认为0
2. flex-grow  
   定义项目的放大比例。默认为0，即如果存在剩余空间，不放大
3. flex-shrink   
   定义项目的缩小比例。默认为1，即如果空间不足，该项目缩小  
4. flex-basis: <length> | auto
   定义了在分配多余空间之前，项目占据的主轴空间（main size）。  
	 浏览器根据这个属性，计算主轴是否有多余空间。它的默认值是auto，即项目本来大小
5. flex  
   flex属性是flex-grow、flex-shrink和flex-basis的简写，默认为0 1 auto。后两个属性可选。  
	 两个快捷值：  
   	auto: 11 auto  
		none: 0 0 auto  
6. align-self: auto | flex-start | flex-end | center | baseline | stretch  
   align-self属性允许单个项目与其它项目有不一样的对齐方式，可覆盖align-items属性。默认为auto，表示继承父元素的align-items属性；如果没有父元素，则等同于stretch

## Grid
grid是一种二维网格布局系统，可用于布局页面主要的区域布局或小型组件。网格是一组相交的水平线和垂直线，它定义了网格的列和行。我们可以将网格元素放置在与这些行与列相关的位置上。
## Block，Inline，Inline-Block


## Responsive



## tailwindcss

## 主流浏览器
内核、css代码前缀