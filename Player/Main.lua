
--[[local app = App:Instance()
local window = Window:Create()

local q = Quad:new()
q.Size = Vector2(0.5, 0.5);
q.Shader = "Shaders\\Color"
q.Texture = "D:/test.png"

window.scene = q

local v = Vector2(3, 3)
print(v.x)]]

function TableToString( table, tab )
	local i = 1
	local str = ''
	str = str .. '{'
	tab = tab or ''

	local first = true
  
	for k, v in pairs( table ) do
		if first then
			first = false
		else
			str = str .. ','
		end
		str = str .. '\r\n' .. tab .. '  '
		if k == i then
			i = i + 1
		else
			str = str .. k .. ' = '
		end
		if type( v ) == 'table' then
			str = str .. TableToString( v, tab .. '  ' )
		elseif type( v ) == 'string' then
			str = str .. '\'' .. v .. '\''
		else
			str = str .. v
		end
	end
  
	if not first then
		str = str .. '\r\n' .. tab
	end
	str = str .. '}'

	return str
end

function Test(table)
	print(TableToString(table))
end

--[[
local t = 
{
	["@"] = "Quad",
	Size = { 0.3, 0.3 },
	Shader = "Shaders\\Color",
	Texture = "D:/test.png",
	Childs = 
	{
		{
			Class = "Quad",
			Size = { 0.3, 0.3 },
			Shader = "Shaders\\Color",
			Texture = "D:/test.png",
			Childs = {}
		}
	}
}

app:StartMainLoop();]]