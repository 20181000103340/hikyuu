# Dependency Tracker

## Module Dependencies

格式说明:
- `<`: 行依赖列
- `>`: 列依赖行
- `x`: 相互依赖
- `d`: 文档依赖
- `o`: 无依赖（对角线）
- `n`: 已验证无依赖
- `p`: 待验证
- `s`: 语义依赖

## Core Modules

|           | hikyuu | hikyuu_cpp | hikyuu_pywrap | test_data |
|-----------|--------|------------|---------------|-----------|
|hikyuu     |   o    |     <      |      <        |    n      |
|hikyuu_cpp |   >    |     o      |      >        |    n      |
|hikyuu_pywrap| >    |     <      |      o        |    n      |
|test_data  |   n    |     n      |      n        |    o      |

注意：此文件为初始版本，需要使用 dependency_processor.py 工具进行更新和维护。

## 待办事项
- [ ] 安装 cline_utils 工具
- [ ] 使用 dependency_processor 重新生成完整依赖关系
- [ ] 验证所有标记为 'p' 的依赖关系
- [ ] 更新模块间的具体依赖说明
