echo "请输入一个10以内的数字"
read var
case $var in
	"1") echo "one";;
	"2") echo "two";;
	*) echo "unknown"
esac
echo "欢迎下次使用！"
